import isotp

sock = isotp.socket()
sock.set_fc_opts(stmin=5, bs=10)


sock2 = isotp.socket()

sock.bind("vcan0", isotp.Address(rxid=0x123, txid=0x124))
sock2.bind("vcan0", isotp.Address(rxid=0x124, txid=0x123))

sock.send(b"Hello this is a long string")

print(sock2.recv())