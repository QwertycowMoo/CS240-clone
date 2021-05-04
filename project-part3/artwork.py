from flask import Blueprint, send_file, request, jsonify
import requests

artwork_server = Blueprint("artwork_server", __name__)

# POST
@artwork_server.route('/<key>', methods=["POST"])
def post_image(key):
  return '', 500
