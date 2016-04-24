# GNUNets
The GNU Neural Network Library, created by Omar J Makke
Pleased to announce version 0.1.0

You can simply use include the header files under activation, network, and parts.

Push i to enter edit mode. When in edit mode, type demo. Not all items in the menu are implemented yet.

Demo will create input as time axis (size 1), output as sine and cosine waves (size 2). 

Short manual:
Create comma delimited text files for inputs and outputs. Make sure they have same number of rows. For reference, check the logicinput.txt and logicoutput.txt files. 

These files are the inputs and outputs for an XOR with 2 inputs.

Once created, run GNUNets.

Type:

    cn(2,5(tanh),5(tanh),1(tanh))

This will create a classic fully connected network (cn) with 4 layers, 2 of which are hidden. All layers have TANH as activation function.

Type:

    use(1)

This will use network labeled as #1. You should select your network label. You can have many networks created, but can only use 1 network at a time.


Type:

    set_io(../logicinput,../logicoutput)

This will load the inputs and outputs to the network. If the network warns about errors, double check to make sure that your input layer (2) matches the input file columns, and the output layer (1) matches the output rows


Type:

    train(0.1, 20000, 0.01)

Basically, train(target error, epoch, learning rate). Watch the network learn.


Type:

    eval(0.2, 0.9) 

To evaluate the network output for the input vector [0.2, 0.9]

If the network doesn't converge, you can reset the weights to new random values. Make sure you have selected a network.
Type:

    reset

You can now train the new network.
You can also retrain the network using the previous parameters you used. If you didn't pass parameters, this will not work as initial values are not suitable "on purpose".
Type:

    retrain
    
For demonstration purposes, a function called plotSquare is created. It only works for networks with 2 inputs and 1 output. It plots a square image where the input (x,y) is the network input, and the color is the output. This is to demonstrate learning with gates.
Type:

    plotSquare(0,0.01,1)
    
This will generate inputs: x from 0 to 1 step 0.01, y from 0 to 1 step 0.01, and feeds the network with all the generated input, and draws the output as pixel error. 
Note: This works only for positive inputs. It is for demonstration only.


# Next Release
Create easy way to test and validate network.
