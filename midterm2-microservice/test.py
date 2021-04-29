import requests
import random

host = "http://127.0.0.1:5000"

def print_response(r):
  print(f"- Response: {r.status_code}")
  if r.text:
    print(f"- Text: {r.text}")


# == From Problem Example ==

# Wade checks in
r = requests.put(f"{host}/guest/waf")
print("PUT /guest/waf")
print_response(r)

# Natalia checks in
r = requests.put(f"{host}/guest/natalia")
print("PUT /guest/natalia")
print_response(r)

# Chancellor Jones checks in
r = requests.put(f"{host}/guest/jones")
print("PUT /guest/jones")
print_response(r)

# Chancellor Jones gets room service
r = requests.get(f"{host}/guest/jones")
print("GET /guest/jones")
print_response(r)

# Natalia checks out
r = requests.delete(f"{host}/guest/natalia")
print("DELETE /guest/natalia")
print_response(r)

# Provost Cangellaris checks in
r = requests.put(f"{host}/guest/cangellaris")
print("PUT /guest/cangellaris")
print_response(r)

# Natalia is searched for
r = requests.get(f"{host}/guest/natalia")
print("GET /guest/natalia")
print_response(r)
