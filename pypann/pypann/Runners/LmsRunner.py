#
# LmsRunner
#


from ..Core import *

def init_net(net):
    net.lms_attributes.learning_rate = 0.3
    net.lms_attributes.learning_momentum = 0.5
    net.lms_attributes.epoch = 1
    net.lms_attributes.annealing_tsc = 10

def init_neuron(neuron):
    neuron.lms_attributes = Attributes()

def init_link(link):
    link.lms_attributes = Attributes()
    link.lms_attributes.last_delta_w = 0

def lms_runner(neuron, net):
    assert(isinstance(neuron, Neuron))
    assert(isinstance(net, Net))
    assert(hasattr(net, "lms_attributes"))

    if not hasattr(neuron, "lms_attributes"):
        init_neuron(neuron)

    #local_gradient = desired_output - actual_output = error - for output neuron
    #local_gradient = weighted sum of upstream neurons local_gradients
    if hasattr(neuron.lms_attributes, "error"):
        neuron.lms_attributes.local_gradient = neuron.lms_attributes.error #output neuron
    else:
        neuron.lms_attributes.local_gradient = 0

    for link in neuron._links_out:
        neuron.lms_attributes.local_gradient += link.to().lms_attributes.local_gradient * link.weight().value()
    #Now neuron.lms_attributes.localGradient contains error (known error for outer layer and weighted sum of
    #local gradients of all upstream neurons for other layers)

    """
    Save actual local gradient value
    Note: we assume that input neuron(it's activation function = Linear)
    has activation function y = x, so dy/dx = 1
    grad = error * df(receptiveField)/dx, but df/dx usually less preferable then df/dy,
    grad = error * df(activationValue)/dy (see Simon Haykin, 2nd edition, p235)
    """
    neuron.lms_attributes.local_gradient *= neuron.tf.df(neuron.output);

    #Update weights
    #Simulated annealing, rate = basic_rate / ( 1 + epoch / time_seek_constant)
    #When epoch -> inf, rate -> basic_rate / epoch
    lr = net.lms_attributes.learning_rate / (1 + (net.lms_attributes.epoch / net.lms_attributes.annealing_tsc));

    #Comment: Na --w--> Nb
    #w is updated while processing Na
    for link in neuron._links_out:
        #See Haykin, p241
        #Ni -> Nj
        #dWj(n) = a*(Wj(n-1)) + learning_rate * local_gradient_j * Yi
        dw = lr * link.to().lms_attributes.local_gradient * neuron.output

        #Momentum
        if not hasattr(link, "lms_attributes"):
            init_link(link)
        dw += net.lms_attributes.learning_momentum * link.lms_attributes.last_delta_w
        link.lms_attributes.last_delta_w = dw

        #Apply dw
        link.weight().add_value(dw)


