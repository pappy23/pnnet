from django.http import HttpResponse
from django.shortcuts import render_to_response

import xmlrpclib

from main.models import *

def faces_list_all(request):
    all_faces = Face.objects.all()
    return render_to_response('faces_list_all.html', {'all_faces': all_faces})

def datasets_list_all(request):
    rpc = xmlrpclib.Server(Setting.objects.get(name='rpc_target').value)
    all_datasets = map(rpc.datasets.get_dataset, rpc.datasets.get_id_list())
    return render_to_response('datasets_list_all.html', {'datasets': all_datasets})

def logs_list_all(request):
    all_logs = Log.objects.all().order_by('-time')
    return render_to_response('logs_list_all.html', {'all_logs': all_logs})
