from django.http import HttpResponse,HttpResponseRedirect
from django.shortcuts import render_to_response
from django import forms
from django.template import RequestContext

from main.models import *

import xmlrpclib
from datetime import datetime
import os.path


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

def logs_list_all(request):
    all_logs = Log.objects.all().order_by('-time')
    return render_to_response('logs_list_all.html', {'all_logs': all_logs})

def info_list_all(request):
    all_info = TrainInfo.objects.all().order_by('-start_time')
    return render_to_response('info_list_all.html', {'all_info': all_info})

def info_get_graph(request):
    gr_id = request.GET['id']
    log('info_get_graph -> requested graph for info record #{0}'.format(gr_id))

    from matplotlib.backends.backend_agg import FigureCanvasAgg as FigureCanvas
    from matplotlib.figure import Figure
    from matplotlib.dates import DateFormatter
    import numpy as np

    r = TrainInfo.objects.get(id=gr_id)
    raw = eval(r.data)
    if r.info_type == 'test1':
        out_num = []
        desired_data = []
        actual_data = []
        N = 0
        for d in raw['data']:
            out_num.append(N+1)
            N+=1
            desired_data.append(d['desired_output'])
            actual_data.append(d['actual_output'])

        ind = np.arange(N)
        width = 0.35
        fig = Figure()
        ax = fig.add_subplot(111)
        rects1 = ax.bar(ind, desired_data, width, color='r')
        rects2 = ax.bar(ind+width, actual_data, width, color='y')
        ax.set_xlabel('Output neurons')
        ax.set_ylabel('Value')
        ax.set_title('Test result for Net')
        ax.set_xticks(ind+width)
        ax.set_xticklabels(out_num)
        ax.legend( (rects1[0], rects2[0]), ('Desired output', 'Actual output') )

        canvas=FigureCanvas(fig)
        response=HttpResponse(content_type='image/png')
        canvas.print_png(response)
        return response

    if r.info_type == 'train':
        epochs = []
        train_errors = []
        test_errors = []
        for d in raw:
            epochs.append(d['epoch'])
            train_errors.append(d['train_error'])
            test_errors.append(d['test_error'])

        fig=Figure()
        ax=fig.add_subplot(111)
        ax.set_xscale('log')
        ax.plot(epochs, train_errors, 'b-', label='Train error')
        ax.plot(epochs, test_errors, 'r-', label='Test error')
        ax.set_title('Train of Net')
        ax.set_xlabel('Epochs')
        ax.set_ylabel('Error')
        ax.legend(loc='best')

        canvas=FigureCanvas(fig)
        response=HttpResponse(content_type='image/png')
        canvas.print_png(response)
        return response

    if r.info_type == 'test_set':
        return HttpResponse("Can't plot graph for {0} data".format(r.info_type))

def nets_actions(request):
    return render_to_response('nets_actions.html', {'net_id': request.GET['id']})

def nets_rename(request):
    class MyForm(forms.Form):
        name = forms.CharField()

    if request.method == 'POST':
        f = MyForm(request.POST)
        if f.is_valid():
            log("nets_rename -> Rename net #{0} to '{1}'".format(request.GET['net_id'], f.cleaned_data['name']))
            rpc = xmlrpclib.Server(Setting.objects.get(name='rpc_target').value)
            try:
                rpc.nets.rename(int(request.GET['net_id']), f.cleaned_data['name'])
                log("nets_rename -> OK")
            except Exception as e:
                log("nets_rename -> RPC failed: {0}".format(e))
            return HttpResponseRedirect("/log")
    else:
        f = MyForm()

    return render_to_response('nets_rename.html', {'net_id':request.GET['net_id'], 'form': f}, context_instance=RequestContext(request))

def nets_showsize(request):
    log("nets_showsize -> Requested size of net #{0}".format(request.GET['net_id']))
    rpc = xmlrpclib.Server(Setting.objects.get(name='rpc_target').value)
    try:
        data = rpc.nets.get_size(int(request.GET['net_id']))
        log("nets_showsize -> OK")
        return render_to_response('nets_showsize.html', { 'net_id':request.GET['net_id'], 'data':data })
    except Exception as e:
        log("nets_showsize -> RPC failed: {0}".format(e))
        return HttpResponseRedirect("/log")

def nets_load(request):
    log("nets_load -> Requested load of net #{0}".format(request.GET['net_id']))
    rpc = xmlrpclib.Server(Setting.objects.get(name='rpc_target').value)
    try:
        rpc.nets.load(int(request.GET['net_id']))
        log("nets_load -> OK")
    except Exception as e:
        log("nets_load -> RPC failed: {0}".format(e))

    return HttpResponseRedirect("/log")

def nets_save(request):
    log("nets_save -> Requested save of net #{0}".format(request.GET['net_id']))
    rpc = xmlrpclib.Server(Setting.objects.get(name='rpc_target').value)
    try:
        rpc.nets.save(int(request.GET['net_id']))
        log("nets_save -> OK")
    except Exception as e:
        log("nets_save -> RPC failed: {0}".format(e))

    return HttpResponseRedirect("/log")

def nets_reset(request):
    class MyForm(forms.Form):
        min_ = forms.FloatField(initial=-0.1)
        max_ = forms.FloatField(initial=+0.1)

    if request.method == 'POST':
        f = MyForm(request.POST)
        if f.is_valid():
            log("nets_reset -> Reset weights of net #{0} ({1}; {2})".format(request.GET['net_id'], f.cleaned_data['min_'], f.cleaned_data['max_']))
            rpc = xmlrpclib.Server(Setting.objects.get(name='rpc_target').value)
            try:
                rpc.nets.reset(int(request.GET['net_id']), float(f.cleaned_data['min_']), float(f.cleaned_data['max_']))
                log("nets_reset -> OK")
            except Exception as e:
                log("nets_reset -> RPC failed: {0}".format(e))
            return HttpResponseRedirect("/log")
    else:
        f = MyForm()

    return render_to_response('nets_reset.html', {'net_id':request.GET['net_id'], 'form': f}, context_instance=RequestContext(request))

def nets_delete(request):
    return render_to_response('nets_stub.html')

def nets_copy(request):
    return render_to_response('nets_stub.html')

def nets_test1(request):
    rpc = xmlrpclib.Server(Setting.objects.get(name='rpc_target').value)

    class MyForm(forms.Form):
        face_id = forms.ChoiceField(label='Face', choices=[(id, id) for id in rpc.faces.get_id_list()])

    if request.method == 'POST':
        f = MyForm(request.POST)
        if f.is_valid():
            log("nets_test1 -> Test net #{0} on face #{1}".format(request.GET['net_id'], f.cleaned_data['face_id']))
            try:
                start_time = datetime.now()
                result = rpc.nets.test1(int(request.GET['net_id']), int(f.cleaned_data['face_id']))
                total_time = datetime.now() - start_time
                TrainInfo.objects.create( \
                        net_id = int(request.GET['net_id']), \
                        info_type='test1', \
                        start_time='{0}-{1}-{2} {3}:{4}:{5}'.format( \
                            start_time.year, \
                            start_time.month, \
                            start_time.day, \
                            start_time.hour, \
                            start_time.minute, \
                            start_time.second), \
                        total_time=total_time.seconds, \
                        description='Test1 net #{0} on face #{1}, mse={2}'.format(request.GET['net_id'], f.cleaned_data['face_id'], result['mse']), \
                        data=str(result))
                log("nets_test1 -> OK")
                return HttpResponseRedirect("/info")
            except Exception as e:
                log("nets_test1 -> RPC failed: {0}".format(e))
                return HttpResponseRedirect("/log")
    else:
        f = MyForm()

    return render_to_response('nets_test1.html', {'net_id':request.GET['net_id'], 'form': f}, context_instance=RequestContext(request))

def nets_test_set(request):
    rpc = xmlrpclib.Server(Setting.objects.get(name='rpc_target').value)

    class MyForm(forms.Form):
        dataset_id = forms.ChoiceField(label='Dataset', choices=[(id, id) for id in rpc.datasets.get_id_list()])

    if request.method == 'POST':
        f = MyForm(request.POST)
        if f.is_valid():
            log("nets_test_set -> Test net #{0} on dataset #{1}".format(request.GET['net_id'], f.cleaned_data['dataset_id']))
            try:
                start_time = datetime.now()
                result = rpc.nets.test_set(int(request.GET['net_id']), int(f.cleaned_data['dataset_id']))
                total_time = datetime.now() - start_time
                TrainInfo.objects.create( \
                        net_id = int(request.GET['net_id']), \
                        info_type='test_set', \
                        start_time='{0}-{1}-{2} {3}:{4}:{5}'.format( \
                            start_time.year, \
                            start_time.month, \
                            start_time.day, \
                            start_time.hour, \
                            start_time.minute, \
                            start_time.second), \
                        total_time=total_time.seconds, \
                        description='Test net #{0} on dataset#{1}, mse={2}'.format(request.GET['net_id'], f.cleaned_data['dataset_id'], result), \
                        data=str(result))
                log("nets_test_set -> OK")
                return HttpResponseRedirect("/info")
            except Exception as e:
                log("nets_test_set -> RPC failed: {0}".format(e))
                return HttpResponseRedirect("/log")
    else:
        f = MyForm()

    return render_to_response('nets_test_set.html', {'net_id':request.GET['net_id'], 'form': f}, context_instance=RequestContext(request))

def nets_train(request):
    rpc = xmlrpclib.Server(Setting.objects.get(name='rpc_target').value)
    dataset_choices = [(id, str(id) + " " + rpc.datasets.get_dataset(id)['name']) for id in rpc.datasets.get_id_list()]

    class MyForm(forms.Form):
        train_dataset_id = forms.ChoiceField(label='Train dataset', choices=dataset_choices, initial=2)
        test_dataset_id  = forms.ChoiceField(label='Test dataset', choices=dataset_choices, initial=3)
        epochs  = forms.IntegerField(label='Epochs', initial=50)
        annealing_tsc = forms.IntegerField(label='Annealing TSC', initial=20)
        stop_error = forms.FloatField(label='Stop error', initial=3.0)
        learning_rate = forms.FloatField(label='Learning rate', initial=0.5)

    if request.method == 'POST':
        f = MyForm(request.POST)
        if f.is_valid():
            log("nets_train -> Train net #{0}".format(request.GET['net_id']))
            try:
                start_time = datetime.now()
                result = rpc.nets.teach(\
                        int(request.GET['net_id']), \
                        int(f.cleaned_data['train_dataset_id']), \
                        int(f.cleaned_data['test_dataset_id']), \
                        int(f.cleaned_data['epochs']), \
                        float(f.cleaned_data['stop_error']), \
                        float(f.cleaned_data['learning_rate']), \
                        int(f.cleaned_data['annealing_tsc']), \
                        )
                total_time = datetime.now() - start_time
                TrainInfo.objects.create( \
                        net_id = int(request.GET['net_id']), \
                        info_type='train', \
                        start_time='{0}-{1}-{2} {3}:{4}:{5}'.format( \
                            start_time.year, \
                            start_time.month, \
                            start_time.day, \
                            start_time.hour, \
                            start_time.minute, \
                            start_time.second), \
                        total_time=total_time.seconds, \
                        description='Train net #{0}\n \
                        train_dataset={1}\n \
                        test_dataset={2}\n \
                        epochs={3}\n \
                        stop_error={4}\n \
                        learning_rate={5}\n \
                        annealing_tsc={6}'.format( \
                            request.GET['net_id'], \
                            f.cleaned_data['train_dataset_id'], \
                            f.cleaned_data['test_dataset_id'], \
                            f.cleaned_data['epochs'], \
                            f.cleaned_data['stop_error'], \
                            f.cleaned_data['learning_rate'], \
                            f.cleaned_data['annealing_tsc']),
                        data=str(result))
                log("nets_train -> OK")
                return HttpResponseRedirect("/info")
            except Exception as e:
                log("nets_train -> RPC failed: {0}".format(e))
                return HttpResponseRedirect("/log")
    else:
        f = MyForm()

    return render_to_response('nets_train.html', {'net_id':request.GET['net_id'], 'form': f}, context_instance=RequestContext(request))

def nets_create_mlp(request):
    class MyForm(forms.Form):
        struct = forms.CharField(initial='8464,10,5', label='Network structure')

    if request.method == 'POST':
        f = MyForm(request.POST)
        if f.is_valid():
            log("nets_create_mlp -> Create MLP ({0})".format(f.cleaned_data['struct']))
            rpc = xmlrpclib.Server(Setting.objects.get(name='rpc_target').value)
            try:
                s = eval(f.cleaned_data['struct'])
                result = rpc.nets.create_mlp(*s)
                log("nets_create_mlp -> OK - new net #{0}".format(result))
            except Exception as e:
                log("nets_rename -> RPC failed: {0}".format(e))
            return HttpResponseRedirect("/log")
    else:
        f = MyForm()

    return render_to_response('nets_create_mlp.html', {'form': f}, context_instance=RequestContext(request))

def nets_create_gcnn(request):
    return render_to_response('nets_stub.html')

