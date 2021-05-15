import org.cryptonode.jncryptor.AES256JNCryptor;
import org.cryptonode.jncryptor.CryptorException;
import org.cryptonode.jncryptor.JNCryptor;
import server.Server;
import terminal.Terminal;

import java.util.Arrays;

public class Main
{
    public static void main(String[] args)
    {
        new Server().start();
    }
}
