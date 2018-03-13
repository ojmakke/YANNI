# YANNI
Yet Another Neural Network Implementation. 

The project is renamed to YANNI. This is how I discovered Lisp.

Push i to enter edit mode. When in edit mode, type demo. Not all items in the menu are implemented yet.

Demo will create input as time axis (size 1), output as sine and cosine waves (size 2). 

Short manual:
Create comma delimited text files for inputs and outputs. Make sure they have same number of rows. For reference, check the logicinput.txt and logicoutput.txt files. 

These files are the inputs and outputs for an XOR with 2 inputs.

Once created, run yanni.

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

Now suppose that you trained your network, but now you want to reinitialize it. Type:

    retrain

After you train your network, you may want to validate an entire set of data. You can use:

    validate(inputfile, outputfile)
    
The results will be written in the output file

# Next Release
The API's will change to Scheme, and will use Guile as extention language.
