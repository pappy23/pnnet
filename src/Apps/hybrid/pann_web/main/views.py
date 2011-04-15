from django.http import HttpResponse
from django.shortcuts import render_to_response
from django import forms
from django.template import RequestContext

import xmlrpclib
from datetime import datetime

from main.models import *

def log(text):
    a = datetime.now()
    Log.objects.create(time='{0}-{1}-{2} {3}:{4}:{5}'.format(a.year, a.month, a.day, a.hour, a.minute, a.second), text=text)

# HTML functions
def index(request):
    return render_to_response('index.html')

def faces_list_all(request):
    rpc = xmlrpclib.Server(Setting.objects.get(name='rpc_target').value)
    try:
        all_faces = map(rpc.faces.get_face, rpc.faces.get_id_list())
    except Exception as e:
        log("faces_list_all -> RPC failed: {0}".format(e))
        return render_to_response('error.html')
    return render_to_response('faces_list_all.html', {'all_faces': all_faces})

def datasets_list_all(request):
    rpc = xmlrpclib.Server(Setting.objects.get(name='rpc_target').value)
    try:
        all_datasets = map(rpc.datasets.get_dataset, rpc.datasets.get_id_list())
    except Exception as e:
        log("datasets_list_all -> RPC failed: {0}".format(e))
        return render_to_response('error.html')
    return render_to_response('datasets_list_all.html', {'datasets': all_datasets})

def nets_list_all(request):
    rpc = xmlrpclib.Server(Setting.objects.get(name='rpc_target').value)
    try:
        all_nets = map(rpc.nets.get_net, rpc.nets.get_id_list())
    except Exception as e:
        log("nets_list_all -> RPC failed: {0}".format(e))
        return render_to_response('error.html')
    return render_to_response('nets_list_all.html', {'nets': all_nets})

def test(request):
    class TestForm(forms.Form):
        field = forms.IntegerField()

    if request.method == 'POST':
        f = TestForm(request.POST)
        if f.is_valid():
            log("test: Form OK; value = {0}".format(f.cleaned_data['field']))
            return render_to_response('index.html')
    else:
        f = TestForm()

    return render_to_response('test.html', {'form': f}, context_instance=RequestContext(request))

def logs_list_all(request):
    all_logs = Log.objects.all().order_by('-time')
    return render_to_response('logs_list_all.html', {'all_logs': all_logs})
