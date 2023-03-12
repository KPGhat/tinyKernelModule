# open('/proc/modulecrypto', 'wb').write('tea encrypt\n')
file = open('/proc/modulecrypto')
# file.write('base64 encrypt\n')
# file.write('adsfasdfasfas')

content = file.readline()
print(content)
file.close()