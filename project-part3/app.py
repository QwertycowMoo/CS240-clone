from flask import Flask
app = Flask(__name__)


from mp8 import mp8_server
app.register_blueprint(mp8_server)

from artwork import artwork_server
app.register_blueprint(artwork_server)










# POST
@app.route('/<key>', methods=["POST"])
def post_image(key):
  


  return f'', 500



# PUT
@app.route('/<key>', methods=["PUT"])
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
@app.route('/<key>', methods=["GET"])
def get_key(key):
  if key not in store:
    return f"Key `{key}` not found.", 404

  index = len(store[key]) - 1
  return jsonify( store[key][index] ), 200

@app.route('/<key>/<version>', methods=["GET"])
def get_key_version(key, version):
  if key not in store:
    return f"Key `{key}` not found.", 404

  version = int(version)
  index = version - 1
  if index >= len(store[key]):
    return f"Key `{key}` does not have v{version}.", 404

  return jsonify( store[key][index] ), 200
  

@app.route('/<key>', methods=["DELETE"])
def delete_key(key):
  if key not in store:
    return f"Key `{key}` not found.", 404

  del store[key]
  return f"Key `{key}` has been deleted.", 200
