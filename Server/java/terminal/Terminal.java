package terminal;

import server.Server;

import java.util.Scanner;

public class Terminal
{

    private final String adminLogin = "AD";
    private final String adminPassword = "123";

    private final Scanner terminalScanner = new Scanner(System.in);;
    private TerminalCommand terminal;


    public Terminal()
    {
        terminal = new TerminalCommand();

        terminalLogin();
        System.out.println("\tstart             :   Start server\n\trestart           :   Restart server\n" +
                "\tshutdown          :   Stop server\n\thelp              :   Full list of commands\n");

        while (true)
        {
            System.out.print(">>  ");
            terminalProcess(terminalScanner.nextLine());

        }
    }


    private void terminalProcess(String command)
    {
        String[] fullCommand = command.split("\\s");


        if(fullCommand[0].compareTo("active") == 0)
        {
            if(fullCommand.length > 1)
            {
                if(fullCommand[1].compareTo("list") == 0)
                    terminal.activeList();
                else
                    terminal.activeSearch();
            }
            else
                terminal.active();
        }
        else if(fullCommand[0].compareTo("all") == 0)
        {
            if(fullCommand.length > 1)
            {
                if(fullCommand[1].compareTo("list") == 0)
                    terminal.allList();
                else
                    terminal.allSearch();
            }
            else
                terminal.all();
        }
        else if(fullCommand[0].compareTo("time") == 0)
        {
            terminal.time();
        }
        else if(fullCommand[0].compareTo("check") == 0)
        {
            terminal.check();
        }
        else if(fullCommand[0].compareTo("help") == 0)
        {
            terminal.help();
        }
        else if(fullCommand[0].compareTo("start") == 0)
        {
            terminal.start();
        }
        else if(fullCommand[0].compareTo("restart") == 0)
        {
            terminal.restart();
        }
        else if(fullCommand[0].compareTo("shutdown") == 0)
        {
            terminal.shutdown();
        }
        else
            System.out.println("Error : Incorrect command");
    }



    private void terminalLogin()
    {
        System.out.println("Enter admin data");

        while (terminalLoginProcess());
        while (terminalPasswordProcess());

        System.out.println("Logged in ");
    }

    private boolean terminalLoginProcess()
    {
        System.out.print("\tLogin    : ");
        if(this.terminalScanner.nextLine().compareTo(adminLogin) != 0)
        {
            System.out.println("Error, Login is incorrect");
            return true;
        }
        else
            return false;
    }

    private boolean terminalPasswordProcess()
    {
        System.out.print("\tPassword : ");
        if(this.terminalScanner.nextLine().compareTo(adminPassword) != 0)
        {
            System.out.println("Error, Password is incorrect");
            return true;
        }
        else
            return false;
    }

}