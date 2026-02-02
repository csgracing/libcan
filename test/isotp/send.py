import isotp

sock = isotp.socket()
sock.set_fc_opts(stmin=5, bs=10)


sock2 = isotp.socket()

sock.bind("vcan0", isotp.Address(rxid=0x123, txid=0x124))
#sock2.bind("vcan0", isotp.Address(rxid=0x124, txid=0x123))

# message that fits in a single frame
sock.send(0x1122334455667788990011223344556677889900.to_bytes(32))

#print(sock2.recv())