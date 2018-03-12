import paho.mqtt.client as mqtt
import threading
import sys

str2 = "b'72277689'"

# The callback for when the client receives a CONNACK response from the server.
def on_connect(client, userdata, flags, rc):
    print("Connected to the mqtt broker "+str(rc))

    # Subscribing in on_connect() means that if we lose the connection and
    # reconnect then subscriptions will be renewed.
    client.subscribe("clientid",0)
	

# The callback for when a PUBLISH message is received from the server.
def on_message(client, userdata, msg):
	print(msg.topic+" "+str(msg.payload))
	str1 = str(msg.payload)
	print("string1 is " + str1)
	print("string2 is " + str2)
	if str1 == str2:
		print ("Client authenticated, sending unlock signal")
		client.publish("lck","1",0)
	else:
		print ("Authentication failed")
	
def on_subscribe(client, userdata, mid, granted_qos):
	print("succesfull subscribe to topic"+str(client))
	
def on_publish(client, userdata, mid):
	print("Thank you")
	
client = mqtt.Client()
client.connect("localhost", 1883, 60)
client.on_connect = on_connect
client.on_subscribe = on_subscribe
client.on_message = on_message
client.on_publish = on_publish
client.loop_forever()