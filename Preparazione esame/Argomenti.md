### Pthread

- **Create**: Crea un nuovo thread.
- **Join**: Attende che un thread specificato termini.
- **Lock e Unlock**: Gestiscono l'accesso esclusivo a una sezione di codice tramite mutex.
- **Wait**: Attende che una condizione specificata diventi vera.
- **Barrier**: Coordina i thread, facendoli attendere finché tutti non raggiungono un punto specifico nel codice.
- **Condition**: Variabili di condizione utilizzate per la sincronizzazione tra i thread.
- **Mutex**: Fornisce il locking mutualmente esclusivo per proteggere la sezione critica.

### MPI

- **Mpi_Send e Mpi_Recv**: Permettono rispettivamente l'invio e la ricezione di messaggi tra processi.
- **Mpi_Init e Mpi_Finalize**: Inizializzano e terminano l'ambiente MPI.
- **Mpi_Comm_size e Mpi_Comm_rank**: Restituiscono il numero di processi in un communicator e il rank (identificativo) del processo chiamante all'interno del communicator.
- **Mpi_Bcast**: Distribuisce un dato dal processo root a tutti gli altri processi nel communicator.
- **Mpi_Barrier**: Sincronizza tutti i processi in un communicator, facendo attendere ciascuno finché tutti non arrivano a questo punto.
- **Mpi_Reduce**: Combina i dati da tutti i processi e li riduce ad un singolo risultato, utilizzando un'operazione specificata (come somma, max, min, ecc.).
- **Mpi_Scatter e Mpi_Gather**: Distribuiscono (scatter) e raccolgono (gather) dati tra tutti i processi in un communicator.
- **Mpi_Isend e Mpi_Irecv**: Versioni non bloccanti di Mpi_Send e Mpi_Recv, che permettono al processo di continuare l'esecuzione mentre si attende il completamento dell'operazione.
- **Mpi_Ssend**: Variante di Mpi_Send che attua un invio sincrono.
- **Mpi_Wait**: Utilizzato con operazioni non bloccanti per attendere il loro completamento.
