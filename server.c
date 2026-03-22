#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

#define PORT 4444

int main() {
    SSL_library_init();
    OpenSSL_add_ssl_algorithms();
    SSL_load_error_strings();

    SSL_CTX *ctx = SSL_CTX_new(DTLS_server_method());

    SSL_CTX_use_certificate_file(ctx, "server.crt", SSL_FILETYPE_PEM);
    SSL_CTX_use_PrivateKey_file(ctx, "server.key", SSL_FILETYPE_PEM);

    int sockfd;
    struct sockaddr_in servaddr, cliaddr;
    socklen_t len = sizeof(cliaddr);

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = INADDR_ANY;

    bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

    printf("🔐 DTLS Server waiting...\n");

    char buffer[1024];

    // 🔥 IMPORTANT: receive first packet to get client info
    int n = recvfrom(sockfd, buffer, sizeof(buffer), MSG_PEEK,
                     (struct sockaddr *)&cliaddr, &len);

    if (n <= 0) {
        perror("recvfrom failed");
        return 1;
    }

    printf("Client detected\n");

    SSL *ssl = SSL_new(ctx);

    BIO *bio = BIO_new_dgram(sockfd, BIO_NOCLOSE);
    BIO_ctrl(bio, BIO_CTRL_DGRAM_SET_CONNECTED, 0, &cliaddr);

    SSL_set_bio(ssl, bio, bio);

    // Handshake
    if (SSL_accept(ssl) <= 0) {
        ERR_print_errors_fp(stderr);
    } else {
        printf("Handshake successful!\n");

        memset(buffer, 0, sizeof(buffer));
        SSL_read(ssl, buffer, sizeof(buffer));

        printf("Client says: %s\n", buffer);
    }

    SSL_free(ssl);
    close(sockfd);
    SSL_CTX_free(ctx);

    return 0;
}
