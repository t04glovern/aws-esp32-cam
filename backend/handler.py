import io
import json
import base64
import os
import uuid
import boto3

from PIL import Image

bucket_name = os.environ['BUCKET_NAME']

def image(event, context):
    # Convert image from base64 payload
    imageStreamBytes = base64.b64decode(event['data'])
    imageFile = Image.open(io.BytesIO(imageStreamBytes))
    imageFileInMemory = io.BytesIO()
    imageFile.save(imageFileInMemory, format='jpeg')
    imageFileData = imageFileInMemory.getvalue()
    
    # Create S3 client and store image
    image_file_name = str(uuid.uuid1()) + '.jpg'
    s3 = boto3.client('s3')
    s3.put_object(Body=imageFileData, Bucket=bucket_name, Key=image_file_name)
    
    # Return details
    body = {
        "file_name": image_file_name,
        "bucket_name": bucket_name
    }

    response = {
        "statusCode": 200,
        "body": json.dumps(body)
    }

    return response
