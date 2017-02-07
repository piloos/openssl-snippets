#include <stdio.h>
#include <openssl/evp.h>
#include <openssl/ec.h>
#include <openssl/bio.h>
#include <openssl/ssl.h>

EVP_PKEY* GenerateECKey(int Nid, EVP_PKEY_CTX *pContext)
{
    EVP_PKEY_CTX *kctx = NULL;
    EVP_PKEY *pkey = NULL, *params = NULL;
    pContext = NULL;

    /* Create the context for parameter generation */
    if(NULL == (pContext = EVP_PKEY_CTX_new_id(EVP_PKEY_EC, NULL)))
    {
        printf("GenerateECKey: error on line %d\n", __LINE__);
        goto exit_func;
    }

    /* Initialise the parameter generation */
    if(1 != EVP_PKEY_paramgen_init(pContext))
    {
        printf("GenerateECKey: error on line %d\n", __LINE__);
        goto exit_func;
    }

    /* We're going to use the specified curve */
    if(1 != EVP_PKEY_CTX_set_ec_paramgen_curve_nid(pContext, Nid))
    {
        printf("GenerateECKey: error on line %d\n", __LINE__);
        goto exit_func;
    }

    /* Create the parameter object params */
    if (!EVP_PKEY_paramgen(pContext, &params))
    {
        printf("GenerateECKey: error on line %d\n", __LINE__);
        goto exit_func;
    }

    /* Create the context for the key generation */
    if(NULL == (kctx = EVP_PKEY_CTX_new(params, NULL)))
    {
        printf("GenerateECKey: error on line %d\n", __LINE__);
        goto exit_func;
    }

    /* Generate the key */
    if(1 != EVP_PKEY_keygen_init(kctx))
    {
        printf("GenerateECKey: error on line %d\n", __LINE__);
        goto exit_func;
    }

    if (1 != EVP_PKEY_keygen(kctx, &pkey))
    {
        printf("GenerateECKey: error on line %d\n", __LINE__);
        goto exit_func;
    }

exit_func:

    if (kctx) {
        EVP_PKEY_CTX_free(kctx);
    }

    if (pkey) {
        printf("GenerateECKey: new key generated!\n");
    }
    else {
        printf("GenerateECKey: ERROR no new key generated!\n");
    }

    return pkey;
}

int main()
{
    EVP_PKEY_CTX* m_KeyCtx = NULL;
    EVP_PKEY* pkey = NULL;
    BIO *out = NULL;
    char buf[4096];
    int ret, len, exit;

    printf("off we go!\n");

    SSL_library_init();
    SSL_load_error_strings();
    ERR_load_BIO_strings();
    OpenSSL_add_all_algorithms();

    pkey = GenerateECKey(729, m_KeyCtx);
    if (pkey) {
        out = BIO_new(BIO_s_mem());
        ret = EVP_PKEY_print_private(out, pkey, 0, NULL);
        printf("print private returned %d\n", ret);
        len = BIO_read(out, (void*) buf, 4096);
        printf("%d bytes read from bio\n", len);
        printf("\n%s\n\n", buf);
        exit = 0;
    }
    else {
        printf("Could not create private key!\n");
        exit = 1;
    }

    printf("bye bye!\n");
    return exit;
}
