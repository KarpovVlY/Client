package server;

import com.mongodb.client.*;
import com.mongodb.client.model.Filters;
import org.bson.Document;

import java.util.Objects;
import java.util.logging.Level;
import java.util.logging.Logger;

public class Mongo
{
    private MongoClient mongoClient;
    private MongoDatabase mongoDatabase;
    private static MongoCollection<Document> users;


    Mongo()
    {
        Logger mongoLogger = Logger.getLogger( "org.mongodb.driver" );
        mongoLogger.setLevel(Level.SEVERE);

        try
        {
            this.mongoClient = MongoClients.create();

            mongoDatabase = mongoClient.getDatabase("server");
            users = mongoDatabase.getCollection("users");
        }
        catch (Exception e) { System.err.println(e.getMessage()); }
    }





    /** User commands
     *
     */
    public static void addNewUser(String usernameValue, String passwordValue, String nameValue, String surnameValue, String emailValue)
    {
        Document document = new Document();
        document.put("username", usernameValue);
        document.put("password", passwordValue);
        document.put("name", nameValue);
        document.put("surname", surnameValue);
        document.put("email", emailValue);

        users.insertOne(document);
    }

    public static boolean checkUserExistFull(String usernameValue, String passwordValue)
    {
        return users.find(Filters.and(new Document("username", usernameValue), new Document("password", passwordValue))).first() != null;
    }

    public static boolean checkUserExistPart(String usernameValue)
    {
        return users.find(new Document("username", usernameValue)).first() != null;
    }

    public static String getEmail(String usernameValue, String passwordValue)
    {
        return Objects.requireNonNull(users.find(Filters.and(new Document("username", usernameValue), new Document("password", passwordValue))).first()).getString("email");
    }


    /** Notes commands
     *
     */
    public static void dropNote(String usernameValue, String nameValue, String descriptionValue, String contentValue)
    {
        users.updateOne( new Document("username", usernameValue),
                new Document().append("$pull", new Document("notes",
                        Filters.and(
                                new Document("name", nameValue),
                                new Document("description", descriptionValue),
                                new Document("content", contentValue)))));
    }

    public static void insertNewNote(String usernameValue, String nameValue, String descriptionValue, String contentValue)
    {
        Document document = new Document();
        document.put("name", nameValue);
        document.put("description", descriptionValue);
        document.put("content", contentValue);

        users.updateOne( Filters.eq("username", usernameValue), new Document().append("$push", new Document("notes", document)));
    }


    /** Contacts commands
     *
     */
    public static void insertNewContact(String usernameValue, String nameValue, String descriptionValue, String phoneValue, String emailValue, String contentValue)
    {
        Document document = new Document();
        document.put("name", nameValue);
        document.put("description", descriptionValue);
        document.put("phone", phoneValue);
        document.put("email", emailValue);
        document.put("content", contentValue);

        users.updateOne( Filters.eq("username", usernameValue), new Document().append("$push", new Document("contacts", document)));
    }

    public static void dropContact(String usernameValue, String nameValue, String descriptionValue, String phoneValue, String emailValue, String contentValue)
    {
        users.updateOne( new Document("username", usernameValue),
                new Document().append("$pull", new Document("contacts",
                        Filters.and(
                                new Document("name", nameValue),
                                new Document("description", descriptionValue),
                                new Document("phone", phoneValue),
                                new Document("email", emailValue),
                                new Document("content", contentValue)))));
    }


    /** Storage commands
     *
     */
    public static void insertNewStorage(String usernameValue, String nameValue, String descriptionValue, String loginValue, String passwordValue, String infoValue, String contentValue)
    {
        Document document = new Document();
        document.put("name", nameValue);
        document.put("description", descriptionValue);
        document.put("login", loginValue);
        document.put("password", passwordValue);
        document.put("info", infoValue);
        document.put("content", contentValue);

        users.updateOne( Filters.eq("username", usernameValue), new Document().append("$push", new Document("storages", document)));
    }


    public static void dropStorage(String usernameValue, String nameValue, String descriptionValue, String loginValue, String passwordValue, String infoValue, String contentValue)
    {
        users.updateOne( new Document("username", usernameValue),
                new Document().append("$pull", new Document("storages",
                        Filters.and(
                                new Document("name", nameValue),
                                new Document("description", descriptionValue),
                                new Document("login", loginValue),
                                new Document("password", passwordValue),
                                new Document("info", infoValue),
                                new Document("content", contentValue)))));
    }


}
