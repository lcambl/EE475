from django.shortcuts import render
from django.http import HttpResponse, JsonResponse
from django.views import generic
from rest_framework.views import APIView
from rest_framework.response import Response
from .serializers import ReadingSerializer
from rest_framework.parsers import JSONParser
from .models import Reading
# Create your views here.

class ReadingView(APIView):
    queryset = Reading.objects.all()
    
    # def get(self, request):
    #     return HttpResponse([reading.sensor_val for reading in Reading.objects.all()])

    def reading_list(request):

        if request.method == 'GET':
            readings = Reading.objects.all()
            serializer = ReadingSerializer(readings, many=True)
            return JsonResponse(serializer.data, safe=False)
        elif request.method == 'POST':
            data = JSONParser().parse(request)
            serializer = ReadingSerializer(data=data)
            if serializer.is_valid():
                serializer.save()
                return JsonResponse(serializer.data, status=201)
            return JsonResponse(serializer.errors, status=400)
            


def index(request):
    return HttpResponse("Index to view sensor readings.")