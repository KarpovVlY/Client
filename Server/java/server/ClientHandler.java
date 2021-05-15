package server;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.net.Socket;
import java.util.ArrayList;
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.FutureTask;

class ClientHandler extends Thread
{

    private final ArrayList<Client> clientArrayList;

    ClientHandler(ArrayList<Client> clientArrayList)
    {
        this.clientArrayList = clientArrayList;
    }


   public void dropClient(Client client)
   {
        FutureTask<Void> clientProcessTask =  new FutureTask<>(new DropClientCallable(clientArrayList, client));
        new Thread(clientProcessTask).start();
        System.err.println("Dropping started");
   }


    public void processClient(Socket socket)
    {

        for(Client client : clientArrayList)
            if(client.getClientSocket() == socket)
                return;

        Client newClient = new Client(socket, this);
        clientArrayList.add(newClient);

        newClient.start();
    }



    public Callable<Void> task = () ->
    {
        int a;

        System.out.println("Here");
        return null;

    };





    @Override
    public void run()
    {
        String word;


    }


}


class Queue
{
    private Client client;
    private ArrayList<Order> orders;


    Queue(Client client)
    {
        this.client = client;
        this.orders = new ArrayList<>();
    }


    public void addOrder(Order order)
    {
        this.orders.add(order);
    }
}

class Order
{

    String command;


    Order()
    {

    }
}
