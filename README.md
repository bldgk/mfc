# Mesh Format Converter

> The most useless mesh converter ever written. In 2018 this seemed like a good idea.

C++ microservice for converting 3D mesh files between formats via HTTP API (2018).

## Run

```bash
docker build -t mfc .
docker run -p 3653:3653 -v $PWD:/data mfc
```

## API

**File paths** (server-side files):
```bash
curl -X POST http://localhost:3653/convert \
  -H "Content-Type: application/json" \
  -d '{"files":["/data/model.stl"],"format":"ctm","options":{}}'
```

**Base64** (send and receive data as JSON):
```bash
curl -X POST http://localhost:3653/convert-data \
  -H "Content-Type: application/json" \
  -d '{"data":"<base64>","from":"obj","to":"ctm","options":{}}'
```

**Raw file** (binary in → binary out, text formats only):
```bash
curl --data-binary @model.obj "http://localhost:3653/convert-file?from=obj&to=ctm" -o model.ctm
```

## Supported Formats

STL, OBJ, PLY, 3DS, CTM (OpenCTM), DAE (Collada), OFF, LWO, WRL

## Options

```json
{
  "scale": 1.0,
  "upaxis": "Y",
  "flip": true,
  "calc-normals": true,
  "method": "mg2",
  "level": 5
}
```

## Stack

C++14, evpp (HTTP server), OpenCTM, nlohmann/json, glog
