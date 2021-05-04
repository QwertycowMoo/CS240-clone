from flask import Blueprint, render_template, request, jsonify
mp8_server = Blueprint("mp8_server", __name__)

store = {}


# PUT
@mp8_server.route('/<key>', methods=["PUT"])
def put(key):
  if key not in store:
    store[key] = []
    version = 1
  else:
    version = len(store[key]) + 1

  store[key].append({
    "version": version,
    "value": request.data.decode("utf-8")
  })

  return f"Key `{key}` added as v{version}.", 200


# GET /<key>
@mp8_server.route('/<key>', methods=["GET"])
def get_key(key):
  if key not in store:
    return f"Key `{key}` not found.", 404

  index = len(store[key]) - 1
  return jsonify( store[key][index] ), 200


# GET /<key>/<version>
@mp8_server.route('/<key>/<version>', methods=["GET"])
def get_key_version(key, version):
  if key not in store:
    return f"Key `{key}` not found.", 404

  version = int(version)
  index = version - 1
  if index >= len(store[key]):
    return f"Key `{key}` does not have v{version}.", 404

  return jsonify( store[key][index] ), 200


# DELETE /<key>
@mp8_server.route('/<key>', methods=["DELETE"])
def delete_key(key):
  if key not in store:
    return f"Key `{key}` not found.", 404

  del store[key]
  return f"Key `{key}` has been deleted.", 200
