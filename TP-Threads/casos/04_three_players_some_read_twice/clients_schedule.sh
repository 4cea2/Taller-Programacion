echo 'Atacar' >> __client_0_pipe__
echo 'Leer 1' >> __client_0_pipe__
echo 'Leer 2' >> __client_1_pipe__
echo 'Leer 2' >> __client_2_pipe__

# Agrego el sleep para asegurarme que el server envia la
# accion de revivir.
sleep 4

echo 'Salir' >> __client_0_pipe__
echo 'Salir' >> __client_1_pipe__
echo 'Salir' >> __client_2_pipe__
