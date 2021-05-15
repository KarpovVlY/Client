package server;

import java.io.*;
import java.net.Socket;
import java.security.SecureRandom;


public class Client extends Thread
{
    private final ClientHandler clientHandler;

    private final Socket clientSocket;

    private BufferedReader reader;
    private BufferedWriter writer;



    private String requestCode = null;

    private final String[] data = new String[2];
    private final String[] registrationData = new String[5];


    Client(Socket clientSocket, ClientHandler clientHandler)
    {
        System.err.println("Client created");

        this.clientSocket = clientSocket;
        this.clientHandler = clientHandler;
    }


    @Override
    public void run()
    {
        System.err.println("Client connected");

        try
        {
            reader = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
            writer = new BufferedWriter(new OutputStreamWriter(clientSocket.getOutputStream()));

        }
        catch (Exception e) { System.err.println(e.getMessage()); }



        String command;
        String[] commandItems;
        while(true)
        {
            try
            {
                command = reader.readLine();
                System.out.println(command);


                commandItems = command.split(":");
                command = commandItems[0];

                if(command.compareTo("MC_NEW_NOTE") == 0)
                {
                    Mongo.insertNewNote(data[0], commandItems[1], commandItems[2], commandItems[3]);
                }
                else if(command.compareTo("MC_NEW_CONTACT") == 0)
                {
                    Mongo.insertNewContact(data[0], commandItems[1], commandItems[2], commandItems[3], commandItems[4], commandItems[5]);
                }
                else if(command.compareTo("MC_NEW_STORAGE") == 0)
                {
                    Mongo.insertNewStorage(data[0], commandItems[1], commandItems[2], commandItems[3], commandItems[4], commandItems[5], commandItems[6]);
                }
                else if(command.compareTo("MC_LOGIN") == 0)
                {
                    if(Mongo.checkUserExistFull(commandItems[1], commandItems[2]))
                    {
                        sendLoggedRequest(Mongo.getEmail(commandItems[1], commandItems[2]));

                        data[0] = commandItems[1];
                        data[1] = commandItems[2];

                        writeIntermediateLogged();
                    }
                    else
                        writeWrongLogged();
                }
                else if(command.compareTo("MC_REGISTER") == 0)
                {
                    if(!Mongo.checkUserExistPart(commandItems[3]))
                    {
                        sendRegistrationRequest(commandItems[4]);

                        registrationData[0] = commandItems[3];
                        registrationData[1] = commandItems[5];
                        registrationData[2] = commandItems[1];
                        registrationData[3] = commandItems[2];
                        registrationData[4] = commandItems[4];

                        writeIntermediateRegistered();
                    }
                    else
                        writeWrongRegistered();
                }
                else if(command.compareTo("MC_DROP_NOTE") == 0)
                {
                    Mongo.dropNote(data[0], commandItems[1], commandItems[2], commandItems[3]);
                }
                else if(command.compareTo("MC_DROP_CONTACT") == 0)
                {
                    Mongo.dropContact(data[0], commandItems[1], commandItems[2], commandItems[3], commandItems[4], commandItems[5]);
                }
                else if(command.compareTo("MC_DROP_STORAGE") == 0)
                {
                    Mongo.dropStorage(data[0], commandItems[1], commandItems[2], commandItems[3], commandItems[4], commandItems[5], commandItems[6]);
                }
                else if(command.compareTo("MC_EDIT_NOTE") == 0)
                {
                    Mongo.dropNote(data[0], commandItems[1], commandItems[2], commandItems[3]);
                    Mongo.insertNewNote(data[0], commandItems[4], commandItems[5], commandItems[6]);
                }
                else if(command.compareTo("MC_EDIT_CONTACT") == 0)
                {
                    Mongo.dropContact(data[0], commandItems[1], commandItems[2], commandItems[3], commandItems[4], commandItems[5]);
                    Mongo.insertNewContact(data[0], commandItems[1], commandItems[2], commandItems[3], commandItems[4], commandItems[5]);
                }
                else if(command.compareTo("MC_EDIT_STORAGE") == 0)
                {
                    Mongo.dropStorage(data[0], commandItems[1], commandItems[2], commandItems[3], commandItems[4], commandItems[5], commandItems[6]);
                    Mongo.insertNewStorage(data[0], commandItems[1], commandItems[2], commandItems[3], commandItems[4], commandItems[5], commandItems[6]);
                }
                else if(command.compareTo("MC_LOGGED_REQUEST") == 0)
                {
                    if(requestCode != null)
                    {
                        if(requestCode.compareTo(commandItems[1]) == 0)
                        {
                            writeSuccessLogged();
                            requestCode = null;
                        }
                        else
                            writeWrongLogged();
                    }
                    else
                        writeWrongLogged();
                }
                else if(command.compareTo("MC_REGISTRATION_REQUEST") == 0)
                {
                    if(requestCode != null)
                    {
                        if(requestCode.compareTo(commandItems[1]) == 0)
                        {
                            Mongo.addNewUser(registrationData[0], registrationData[1], registrationData[2], registrationData[3], registrationData[4]);

                            writeSuccessRegistered();
                            requestCode = null;
                        }
                        else
                            writeWrongRegistered();
                    }
                    else
                        writeWrongRegistered();
                }
                else if(command.compareTo("MC_STOP") == 0)
                {
                    clientHandler.dropClient(this);
                    clientSocket.close();
                    break;
                }
                else
                {

                }

            }
            catch (Exception e) { System.err.println(e.getMessage()); }
        }
    }


    private void sendRegistrationRequest(String email)
    {
        requestCode = generateRegistrationRequestCode();
        Mail.send("Подтверждение регистрации", requestCode, email);
    }

    private void sendLoggedRequest(String email)
    {
        requestCode = generateRegistrationRequestCode();
        Mail.send("Подтверждение входа", requestCode, email);
    }



    private void writeSuccessLogged() throws IOException
    {
        writer.write("MS_SUCCESS_LOGGED");
        writer.flush();
    }

    private void writeIntermediateLogged() throws IOException
    {
        writer.write("MS_INTERMEDIATE_LOGGED");
        writer.flush();
    }

    private void writeWrongLogged() throws IOException
    {
        writer.write("MS_WRONG_LOGGED");
        writer.flush();
    }


    private void writeSuccessRegistered() throws IOException
    {
        writer.write("MS_SUCCESS_REGISTERED");
        writer.flush();
    }

    private void writeIntermediateRegistered() throws IOException
    {
        writer.write("MS_INTERMEDIATE_REGISTERED");
        writer.flush();
    }

    private void writeWrongRegistered() throws IOException
    {
        writer.write("MS_WRONG_REGISTERED");
        writer.flush();
    }


    public Socket getClientSocket() { return clientSocket; }


    private String generateRegistrationRequestCode()
    {
        StringBuilder requestCode = new StringBuilder();
        SecureRandom secureRandom = new SecureRandom();

        for(short i = 0 ; i < 6 ; i ++)
            requestCode.append(secureRandom.nextInt(9));

        return "V-" + requestCode;
    }

}
