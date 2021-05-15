package server;

import com.mongodb.BasicDBObject;
import com.mongodb.DBObject;
import com.mongodb.client.*;
import com.mongodb.client.model.Filters;
import com.mongodb.client.model.Updates;
import com.mongodb.client.result.UpdateResult;
import org.bson.Document;

import java.net.ServerSocket;
import java.net.Socket;
import java.security.SecureRandom;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.logging.Logger;
import java.util.logging.Level;
import com.mongodb.*;

import javax.print.Doc;

public class Server extends Thread
{

    private static final int SERVER_PORT = 2160;

    private ArrayList<Client> clientArrayList;

    private ClientHandler clientHandler;

    private String generateRegistrationRequestCode()
    {
        StringBuilder requestCode = new StringBuilder();
        SecureRandom secureRandom = new SecureRandom();

        for(short i = 0 ; i < 6 ; i ++)
            requestCode.append(secureRandom.nextInt(9));

        return requestCode.toString();
    }

    public Server()
    {
        clientArrayList = new ArrayList<>();
        clientHandler = new ClientHandler(clientArrayList);
        clientHandler.start();

        new Mail();
        new Mongo();

       // Mongo.addNewUser("meUS", "MEPASS");

/*
            Document document = new Document();
            document.put("name", "nameValue");
            document.put("description", "descriptionValue");
            document.put("content", "contentValue");

            users.updateOne( Filters.eq("username", "USER"),
                    new Document()
                            .append("$push", new Document("notes", document))
                            .append(""));



            Filters.and(
                    new Document("name", "nameValue"),
                    new Document("description", "descriptionValue"),
                    new Document("content", "contentValue"));*/

            //dropNote("USER", "A", "O", "T");
            //addNewUser("USER21", "PASS");
            //insertNewNote("USER", "A", "R", "T");
            //insertNewNote("USER", "56", "jh", "kl");


    }






    @Override
    public void run()
    {
        try
        {
            ServerSocket serverSocket = new ServerSocket(SERVER_PORT);
            System.err.println("Server started");

            Socket socket;


            while(true)
            {
                socket = serverSocket.accept();

                System.err.println("New client connected");

                clientHandler.processClient(socket);
            }

        }
        catch (Exception e) { System.err.println(e.getMessage()); }
    }





    public void check() { System.out.println("Server is active"); }

}
