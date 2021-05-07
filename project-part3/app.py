from flask import Flask, request, jsonify
import requests, PIL
app = Flask(__name__)


from mp8 import mp8_server
app.register_blueprint(mp8_server)

from artwork import artwork_server
app.register_blueprint(artwork_server)

# PUT
@app.route('/<key>', methods=["PUT"])
def post_image(key):
  print("maing app put")
  return f'', 500

