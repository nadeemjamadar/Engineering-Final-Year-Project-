# /usr/bin/env python
# Download the twilio-python library from http://twilio.com/docs/libraries
from twilio.rest import TwilioRestClient

# Find these values at https://twilio.com/user/account
account_sid = "AC3bfb0ba7b72303b6c3361dbb438f54f3"
auth_token = "818e0f4b36efbc5f41c160e5f3f50f97"
client = TwilioRestClient(account_sid, auth_token)

message = client.messages.create(to="+918970107115", from_="+16314860952 ",
                                     body="Parcel received!")