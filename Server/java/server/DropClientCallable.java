package server;

import java.util.ArrayList;
import java.util.concurrent.Callable;

public class DropClientCallable implements Callable<Void>
{
    private final ArrayList<Client> clientArrayList;
    private final Client client;


    public DropClientCallable(ArrayList<Client> clientArrayList, Client client)
    {
        this.clientArrayList = clientArrayList;
        this.client = client;
    }

    @Override
    public Void call()
    {
        clientArrayList.removeIf(client -> this.client == client);
        System.err.println("Client dropped");
        return null;
    }
}
