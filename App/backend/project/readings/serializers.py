from rest_framework import serializers
from .models import Reading

class ReadingSerializer(serializers.Serializer):
    sensor_val = serializers.CharField(max_length=50),
    datetime = serializers.CharField(max_length=100),

    def create(self, validated_data):
        return Reading.objects.create(**validated_data)