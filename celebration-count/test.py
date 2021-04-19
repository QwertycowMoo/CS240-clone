import requests
import random

host = "http://127.0.0.1:5000"

def print_response(r):
  print(f"- Response: {r.status_code}")
  if r.text:
    print(f"- Text: {r.text}")


# == From MP overview ==
r = requests.get(f"{host}/count")
print("GET /count")
print_response(r)

r = requests.put(f"{host}/celebration", "The end of the semester is almost here!")
print("PUT /celebration")
print_response(r)

r = requests.put(f"{host}/celebration", "2020 is almost over!")
print("PUT /celebration")
print_response(r)

r = requests.get(f"{host}/count")
print("GET /count")
print_response(r)

r = requests.get(f"{host}/")
print("GET /")
print_response(r)
