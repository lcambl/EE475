from django.db import models

# Create your models here.
class Reading(models.Model):
    # come up with fields
    sensor_val = models.CharField(max_length=50),
    datetime = models.CharField(max_length=100),
    def __str__(self):
        return (
            f"{self.sensor_val} "
            f"{self.datetime} "
        )