from rest_framework.views import APIView
from rest_framework.response import Response
from rest_framework import status
import numpy as np
import joblib
from django.conf import settings
import os
import json


class BasicAPI(APIView):
    def post(self, request):
        req_data = request.data
        data = {
            'hand_types': req_data.get('hand_types'),
            'palm_positions': req_data.get('palm_positions'),
            'fingers': req_data.get('fingers'),
        }
        model_path = os.path.join(settings.BASE_DIR, 'api/models', 'gesture_recognition_model.pkl')
        clf = joblib.load(model_path)
        thumb_positions = []
        index_positions = []
        middle_positions = []
        ring_positions = []
        pinky_positions = []
        palm_positions = []

        thumb = []
        index = []
        middle = []
        ring = []
        pinky = []

        fingers_string = data['fingers']
        fingers_object = json.loads(fingers_string)
        palm_positions.extend(json.loads(data['palm_positions']))
        thumb_positions.extend(fingers_object['thumb'])
        index_positions.extend(fingers_object['index'])
        middle_positions.extend(fingers_object['middle'])
        ring_positions.extend(fingers_object['ring'])
        pinky_positions.extend(fingers_object['pinky'])

        palm = [np.mean(palm_positions, axis=0), np.std(palm_positions, axis=0), np.cov(palm_positions, rowvar=False).diagonal(), np.sqrt(np.mean(np.square(palm_positions), axis=0))]
        thumb = [np.mean(thumb_positions, axis=0), np.std(thumb_positions, axis=0), np.cov(thumb_positions, rowvar=False).diagonal(), np.sqrt(np.mean(np.square(thumb_positions), axis=0))]
        index = [np.mean(index_positions, axis=0), np.std(index_positions, axis=0), np.cov(index_positions, rowvar=False).diagonal(), np.sqrt(np.mean(np.square(index_positions), axis=0))]
        middle = [np.mean(middle_positions, axis=0), np.std(middle_positions, axis=0), np.cov(middle_positions, rowvar=False).diagonal(), np.sqrt(np.mean(np.square(middle_positions), axis=0))]
        ring = [np.mean(ring_positions, axis=0), np.std(ring_positions, axis=0), np.cov(ring_positions, rowvar=False).diagonal(), np.sqrt(np.mean(np.square(ring_positions), axis=0))]
        pinky = [np.mean(pinky_positions, axis=0), np.std(pinky_positions, axis=0), np.cov(pinky_positions, rowvar=False).diagonal(), np.sqrt(np.mean(np.square(pinky_positions), axis=0))]
        
        features = np.concatenate([palm, thumb, index, middle, ring, pinky]).flatten()

        gesture = clf.predict([features])[0]

        confidence = clf.predict_proba([features])[0][gesture-6]

        return Response({"gesture": gesture, "confidence": confidence}, status=status.HTTP_200_OK)