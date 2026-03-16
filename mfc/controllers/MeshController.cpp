//
// Created by webdev on 21.09.2018.
//

#include "MeshController.h"
#include <fstream>
#include <sstream>
#include <cstdio>
#include <random>


struct NotAObjectException : public std::exception
{
	const char *what() const noexcept final
	{
		return "not a object";
	}
};

// Simple base64 encode/decode
static const std::string b64chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

static std::string base64_encode(const std::string &in) {
	std::string out;
	int val = 0, valb = -6;
	for (unsigned char c : in) {
		val = (val << 8) + c;
		valb += 8;
		while (valb >= 0) {
			out.push_back(b64chars[(val >> valb) & 0x3F]);
			valb -= 6;
		}
	}
	if (valb > -6) out.push_back(b64chars[((val << 8) >> (valb + 8)) & 0x3F]);
	while (out.size() % 4) out.push_back('=');
	return out;
}

static std::string base64_decode(const std::string &in) {
	std::string out;
	std::vector<int> T(256, -1);
	for (int i = 0; i < 64; i++) T[b64chars[i]] = i;
	int val = 0, valb = -8;
	for (unsigned char c : in) {
		if (T[c] == -1) break;
		val = (val << 6) + T[c];
		valb += 6;
		if (valb >= 0) {
			out.push_back(char((val >> valb) & 0xFF));
			valb -= 8;
		}
	}
	return out;
}

static std::string random_id() {
	static std::mt19937 rng(std::random_device{}());
	std::uniform_int_distribution<int> dist(100000, 999999);
	return std::to_string(dist(rng));
}

static std::string read_file(const std::string &path) {
	std::ifstream f(path, std::ios::binary);
	std::ostringstream ss;
	ss << f.rdbuf();
	return ss.str();
}

static void write_file(const std::string &path, const std::string &data) {
	std::ofstream f(path, std::ios::binary);
	f.write(data.data(), data.size());
}


void MeshController::Convert(evpp::EventLoop *loop,
							 const evpp::http::ContextPtr &ctx,
							 const evpp::http::HTTPSendResponseCallback &cb)
{
	(void) loop;
	json j;

	auto timer = std::make_unique<Timer>();
	timer->Note();

	try {
		j = json::parse(ctx->body().ToString());
		if (!j.is_object()) throw NotAObjectException();

		auto options = j.at("options");
		auto files = j.at("files");
		auto format = j.at("format");

		auto meshConverter = std::make_unique<MeshConverter>();
		meshConverter->Convert(files, format, options);

		json message = {
				{"message", "success"},
				{"code",    200}
		};
		cb(message.dump());
	}
	catch (std::exception &e) {
		json err = {
				{"error", e.what()},
				{"code",  400}
		};
		std::cout << timer->Now() << "Error: " << e.what() << std::endl;
		cb(err.dump());
		return;
	}
	std::cout << timer->Now() << ctx->original_uri() << " " << timer->Duration() << " ms" << std::endl;

	ctx->AddResponseHeader("Content-Type", "application/json");
	ctx->AddResponseHeader("Access-Control-Allow-Origin", "*");
}


void MeshController::ConvertData(evpp::EventLoop *loop,
							 const evpp::http::ContextPtr &ctx,
							 const evpp::http::HTTPSendResponseCallback &cb)
{
	(void) loop;
	auto timer = std::make_unique<Timer>();
	timer->Note();

	try {
		json j = json::parse(ctx->body().ToString());
		if (!j.is_object()) throw NotAObjectException();

		std::string data = base64_decode(j.at("data").get<std::string>());
		std::string from_ext = j.at("from").get<std::string>();
		std::string to_ext = j.at("to").get<std::string>();
		json j_options = j.value("options", json::object());

		// Write temp input file
		std::string id = random_id();
		std::string input_path = "/tmp/mfc_" + id + "." + from_ext;
		std::string output_path = "/tmp/mfc_" + id + "." + to_ext;
		write_file(input_path, data);

		// Convert
		Options options;
		auto optionProcessor = std::make_unique<OptionsProcessor>();
		optionProcessor->Process(options, j_options);

		auto meshConverter = std::make_unique<MeshConverter>();
		meshConverter->convert(input_path, output_path, options);

		// Read result
		std::string result = read_file(output_path);
		std::string result_b64 = base64_encode(result);

		// Cleanup
		std::remove(input_path.c_str());
		std::remove(output_path.c_str());

		json response = {
			{"data", result_b64},
			{"format", to_ext},
			{"size", (int)result.size()},
			{"code", 200}
		};
		cb(response.dump());

		std::cout << timer->Now() << " " << from_ext << " -> " << to_ext
				  << " (" << data.size() << " -> " << result.size() << " bytes) "
				  << timer->Duration() << " ms" << std::endl;
	}
	catch (std::exception &e) {
		json err = {{"error", e.what()}, {"code", 400}};
		std::cout << timer->Now() << "Error: " << e.what() << std::endl;
		cb(err.dump());
	}

	ctx->AddResponseHeader("Content-Type", "application/json");
	ctx->AddResponseHeader("Access-Control-Allow-Origin", "*");
}


void MeshController::ConvertFile(evpp::EventLoop *loop,
							 const evpp::http::ContextPtr &ctx,
							 const evpp::http::HTTPSendResponseCallback &cb)
{
	(void) loop;
	auto timer = std::make_unique<Timer>();
	timer->Note();

	try {
		// Get format from query: /convert-file?from=stl&to=ctm
		std::string uri = ctx->original_uri();
		std::string from_ext = "stl", to_ext = "ctm";

		auto parse_param = [&uri](const std::string &key) -> std::string {
			auto pos = uri.find(key + "=");
			if (pos == std::string::npos) return "";
			pos += key.size() + 1;
			auto end = uri.find('&', pos);
			return uri.substr(pos, end == std::string::npos ? std::string::npos : end - pos);
		};

		std::string p_from = parse_param("from");
		std::string p_to = parse_param("to");
		if (!p_from.empty()) from_ext = p_from;
		if (!p_to.empty()) to_ext = p_to;

		std::string body = ctx->body().ToString();

		std::string id = random_id();
		std::string input_path = "/tmp/mfc_" + id + "." + from_ext;
		std::string output_path = "/tmp/mfc_" + id + "." + to_ext;
		write_file(input_path, body);

		Options options;
		auto meshConverter = std::make_unique<MeshConverter>();
		meshConverter->convert(input_path, output_path, options);

		std::string result = read_file(output_path);
		std::remove(input_path.c_str());
		std::remove(output_path.c_str());

		ctx->AddResponseHeader("Content-Type", "application/octet-stream");
		ctx->AddResponseHeader("Access-Control-Allow-Origin", "*");
		cb(result);

		std::cout << timer->Now() << " " << from_ext << " -> " << to_ext
				  << " (" << body.size() << " -> " << result.size() << " bytes) "
				  << timer->Duration() << " ms" << std::endl;
	}
	catch (std::exception &e) {
		json err = {{"error", e.what()}, {"code", 400}};
		cb(err.dump());
	}
}
