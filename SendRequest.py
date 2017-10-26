import speech_recognition as sr
import urllib2 as url

# Record Audio
r = sr.Recognizer()
with sr.Microphone() as source:
    print("Say something!")
    audio = r.listen(source)

# Speech recognition using Google Speech Recognition
try:
    # for testing purposes, we're just using the default API key
    # to use another API key, use `r.recognize_google(audio, key="GOOGLE_SPEECH_RECOGNITION_API_KEY")`
    # instead of `r.recognize_google(audio)`
    str = r.recognize_google(audio)
    str = str.upper()
    print("You said: " + str)
    if str == "LED 1 ON":
        command = "LED1=ON"
    elif str == "LED 1 OFF" or str == "LED 1 OF":
        command = "LED1=OFF"
    elif str == "LED 1 ON" or str == "LED TO ON":
        command = "LED2=ON"
    elif str == "LED 2 OFF" or str == "LED 2 OF" or str == "LED TO OFF" or str == "LED TO OFF":
        command = "LED2=OFF"
    elif str == "LED 3 on":
        command = "LED3=ON"
    elif str == "LED 3 O" or str == "LED 3 OFF":
        command = "LED3=OFF"
    url.urlopen("http://192.168.0.10/"+command).read()

except sr.UnknownValueError:
    print("Google Speech Recognition could not understand audio")
except sr.RequestError as e:
    print("Could not request results from Google Speech Recognition service; {0}".format(e))