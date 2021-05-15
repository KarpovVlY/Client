package terminal;

import server.Server;

public class TerminalCommand
{

    private Server server;

    TerminalCommand()
    {

    }


    public void active()
    {

    }


    public void activeList()
    {

    }


    public void activeSearch()
    {

    }


    public void all()
    {

    }


    public void allList()
    {

    }


    public void allSearch()
    {

    }


    public void start()
    {
        server = new Server();
        server.start();
    }


    public void restart()
    {
        server.interrupt();
        while (!server.isInterrupted());
        server.start();
    }


    public void shutdown()
    {
        server.interrupt();
        server = null;
    }


    public void time()
    {

    }

    public void check ()
    {
        server.check();
    }


    public void help()
    {
        System.out.println("\tcheck             :   Check is server working\n\ttime              :   Get time of server is working\n\tactive            :   Show count of active users\n" +
                "\tactive list       :   Show usernames of active users\n\tactive 'username' :   Show base info of definite user who is active\n\tall               :   Show count of active users\n" +
                "\tall list          :   Show usernames of all users\n\tall 'username'    :   Show base info of definite user ");
    }
}
