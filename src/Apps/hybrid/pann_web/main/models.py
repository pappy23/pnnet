from django.db import models

class Log(models.Model):
    time = models.DateTimeField()
    text = models.TextField()

class Setting(models.Model):
    name = models.CharField(max_length=100)
    value = models.CharField(max_length=100)

