union respuesta switch (int errno) {
  case 0:
    string cadena<>;
  default:
    void;
};

program DNS {
  version DNSv1 {
    respuesta  consultar(string) = 1;
    int        registrar(string, string) = 2;
    int        liberar  (string) = 3;
  } = 1;
} = 0x20000000;