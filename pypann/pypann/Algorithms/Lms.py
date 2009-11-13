#
# Lms
#

from ..Runners import init_net, lms_runner
from Teacher import teach

def lms(net, data):
    """Least Mean Squared algorithm
    
    Implements LMS(gradient descent) algorithm
    """
    if not hasattr(net, "lms_attributes"):
        init_net(net)
    
    #=========================================================================== 
    # Simulated annealing, rate = basic_rate / ( 1 + epoch / time_seek_constant) 
    # When epoch -> inf, rate -> basic_rate / epoch 
    # TODO: move it to lms algorithm
    #===========================================================================
    net.lms_attributes.actual_learning_rate = net.lms_attributes.learning_rate / (1 + (net.lms_attributes.epoch / net.lms_attributes.annealing_tsc));

    teach(net, data, lms_runner)
    net.lms_attributes.epoch += 1
