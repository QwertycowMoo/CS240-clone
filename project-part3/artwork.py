from flask import Blueprint, send_file, request, jsonify
import requests
from PIL import Image
from io import BytesIO

artwork_server = Blueprint("artwork_server", __name__)



# POST
@artwork_server.route('/<key>', methods=["POST"])
def post_image(key):
  print("artwork server put")
  jpg = Image.open(BytesIO(request.data))
  jpg.save("temp.jpg")
   
  r = requests.post(
    "https://api.deepai.org/api/deepdream",
    files={
        'image': open('./temp.jpg', 'rb'),
    },
    headers={'api-key': 'cf1a5000-d0a9-41b9-8929-ae97bd01aa52'}
  )
  if r.status_code != 200 :
    return "There's something wrong with the DeepDream API.", 500

  ret = r.json()
  img_r = requests.get(ret['output_url'])
  img_dream = img_r.content
  print(type(img_dream))
  print("making put request to state server")
  url = "http://localhost:5000/"
  requests.put(url + key, data = img_dream)

  return img_dream, 200
