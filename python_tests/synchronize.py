import socket
import json
from time import sleep
import logging


def trimmed_json(string):
    return json.dumps(string).replace(" ", "")


def heartbeat(ts):
    t = str(int(10))
    body = {"ts": ts}
    body_str = trimmed_json(body)
    header = {"size": str(len(body_str)).zfill(6), "type": t}
    msg = trimmed_json(header) + body_str
    return msg.encode("utf-8")


s = socket.socket()

host = "127.0.0.1"
port = 10000

s.connect((host, port))

logging.basicConfig(level=logging.INFO)

ts = 1000
interval = 0.1
while 1:
    msg = heartbeat(ts)
    logging.info(msg)
    s.send(msg)
    ts += interval
    sleep(interval)
