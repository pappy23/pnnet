from django.http import HttpResponse
from django.shortcuts import render_to_response

from main.models import *

def test(request):
    import xmlrpclib

    # Create an object to represent our server.
    server = xmlrpclib.Server(Setting.get(name='rpc_target'))

    # Call the server and get our result.
    result = server.faces.get_count()

    return HttpResponse("Faces loaded: %d" % result)

def faces_list_all(request):
    all_faces = Face.objects.all()
    return render_to_response('faces_list_all.html', {'all_faces': all_faces})

def logs_list_all(request):
    all_logs = Log.objects.all().order_by('-time')
    return render_to_response('logs_list_all.html', {'all_logs': all_logs})
