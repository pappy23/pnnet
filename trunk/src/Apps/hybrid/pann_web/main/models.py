from django.db import models

class Face(models.Model):
    id = models.AutoField(primary_key=True)
    man = models.IntegerField('Man')
    position = models.IntegerField('Facial expression')
    path = models.CharField(max_length=500)

    def __unicode__(self):
        return "Man: "+self.man.__str__()+"   |   Expression: "+self.position.__str__()+"   |   Path: "+self.path

class Dataset(models.Model):
    name = models.CharField(max_length=100)
    description = models.TextField()

    def __unicode__(self):
        return self.name

class FaceToDataset(models.Model):
    dataset = models.ForeignKey(Dataset)
    face = models.ForeignKey(Face)

class Log(models.Model):
    time = models.DateTimeField()
    text = models.TextField()

class Setting(models.Model):
    name = models.CharField(max_length=100)
    value = models.CharField(max_length=100)

