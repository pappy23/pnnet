from main.models import *
from django.contrib import admin

class FaceAdmin(admin.ModelAdmin):
    list_display = ('id', 'man', 'position', 'path')
admin.site.register(Face, FaceAdmin)

#class DatasetAdmin(admin.ModelAdmin):
#    fields = ['name']
#
#admin.site.register(Dataset, DatasetAdmin)

#admin.site.register(Face)
admin.site.register(Dataset)
admin.site.register(Setting)

class FaceToDatasetAdmin(admin.ModelAdmin):
    list_display = ('dataset', 'face')
admin.site.register(FaceToDataset, FaceToDatasetAdmin)
