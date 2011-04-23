from django.db import models

class Log(models.Model):
    time = models.DateTimeField()
    text = models.TextField()

class Setting(models.Model):
    name = models.CharField(max_length=100)
    value = models.CharField(max_length=100)

class TrainInfo(models.Model):
    net_id = models.IntegerField()
    info_type = models.CharField(max_length=100)
    start_time = models.DateTimeField()
    total_time = models.IntegerField()
    description = models.TextField()
    data = models.TextField()
