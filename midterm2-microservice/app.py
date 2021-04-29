from flask import Flask, request, jsonify
app = Flask(__name__)

rooms = [300, 301, 302, 303, 304]
guests = ["", "", "", "", ""]
# PUT /guest/<guest>
@app.route('/guest/<guest>', methods=["PUT"])
def put_guest(guest):
  for i in range(len(rooms)):
    if not guests[i]:
      guests[i] = guest
      response = {"room": rooms[i],
                  "guest": guest}
      return jsonify(response), 200
  return "No Rooms Available", 400


# DELETE /guest/<guest>
@app.route('/guest/<guest>', methods=["DELETE"])
def delete_guest(guest):
  for i in range(len(rooms)):
    if (guests[i] == guest):
      guests[i] = ""
      response = {"room": rooms[i],
                  "guest": guest}
      return jsonify(response), 200
  return "Guest Not Found", 404


# GET /guest/<guest>
@app.route('/guest/<guest>', methods=["GET"])
def get_guest(guest):
  for i in range(len(rooms)):
    if (guests[i] == guest):
      response = {"room": rooms[i],
                  "guest": guest}
      return jsonify(response), 200
  return "Guest Not Found", 404
