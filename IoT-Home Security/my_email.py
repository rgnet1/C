# import config
import os

import smtplib
from email.mime.text import MIMEText
from email.mime.multipart import MIMEMultipart
from email.mime.image import MIMEImage
from email.mime.base import MIMEBase
from email import encoders

#               send_email()
#   This function sends an email with an attachement
#
# @param: filename - list of files to send.
# @param: to  - array list: name of person I am sending email to
# @param to_email - array list: email of person I am sending email to
# @param sender - array of:  1. Engineer name, 2. engineer email, 3. email password.
def send_email(filename, to, to_email, sender, subject):
    try:
        # Create the root message and fill in the from, to, and subject headers
        # print sender
        # print to
        # print to_email
        engineer = sender[0]
        from_email = sender[1]
        email_password = sender[2]



        msgRoot = MIMEMultipart('related')
        msgRoot['Subject'] = subject
        msgRoot['From'] = from_email
        msgRoot['To'] = ", ".join(to_email)
        msgRoot.preamble = 'This is a multi-part message in MIME format.'

        # Encapsulate the plain and HTML versions of the message body in an
        # 'alternative' part, so message agents can decide which they want to display.
        msgAlternative = MIMEMultipart('alternative')
        msgRoot.attach(msgAlternative)

        msgText = MIMEText('''Your recent project's burn in is complete''')
        msgAlternative.attach(msgText)
        email_begin = "Test email..."
        msgText = MIMEText(email_begin, 'html')
        msgAlternative.attach(msgText)

        # This example assumes the image is in the current directory
        # fp = open('IV_logo.png', 'rb')
        # msgImage = MIMEImage(fp.read())
        # fp.close()

        # # Define the image's ID as referenced above
        # msgImage.add_header('Content-ID', '<image1>')
        # msgRoot.attach(msgImage)

        # Email attachment
        for file in filename:
            # print 'file is ', file
            attachment = open(file, 'rb')

            part = MIMEBase('application', 'octet-stream')
            part.set_payload(attachment.read())
            encoders.encode_base64(part)
            part.add_header('Content-Disposition', "attachment; filename= " + file)

            msgRoot.attach(part)
        # Send e-mail
        # print('hello there')
        smtp = smtplib.SMTP_SSL('smtp.gmail.com', 465)
        smtp.ehlo()
       
        # print('sending email')
        email_user = from_email
        # print(email_user, email_password)
        smtp.login(email_user, email_password) # Returns type tuple
        # print('done logging in')
        # print(to_email)
        # print(from_email)
        smtp.sendmail(from_email, to_email, msgRoot.as_string())
        smtp.quit()
        print("Success: Email sent!")
    except:
        print("Email failed to send.")



def get_email_contents():
    body = '''<p style="text-align: center;">&nbsp;</p>'''
    return body2



import argparse
parser = argparse.ArgumentParser()
parser.add_argument('strings', nargs='+')
args = parser.parse_args()

# FIle list is a list of file names
files_list = args.strings

# print(files_list)

# filename = []
# filename.append('Burn-in-results-016301001233.pdf')
to = []
to.append('Ramzey')
to_email =[]
to_email.append('hnakai@scu.edu')
sender = []
sender.append("Ramzey")
sender.append('rgnet66@gmail.com')
sender.append('PASSWORD_HERE')
subject = 'Home Automation'
send_email(files_list, to, to_email, sender, subject)


