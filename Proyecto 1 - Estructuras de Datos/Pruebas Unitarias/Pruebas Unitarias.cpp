#include "pch.h"
#include "CppUnitTest.h"
#include "../Proyecto 1 - Estructuras de Datos/Navegador.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PruebasUnitarias
{
    TEST_CLASS(PruebasUnitarias)
    {
    public:

        TEST_METHOD(TestCrearNavegador)
        {
            Navegador navegador;
            Assert::AreEqual(1, navegador.numeroTab());
        }

        TEST_METHOD(TestNuevaTab)
        {
            Navegador navegador;
            navegador.nuevaTab();
            Assert::AreEqual(2, navegador.numeroTab());
        }

        TEST_METHOD(TestCerrarTab)
        {
            Navegador navegador;
            navegador.nuevaTab();
            navegador.cerrarTab();
            Assert::AreEqual(1, navegador.numeroTab());
        }
        TEST_METHOD(TestCrearMarcador)
        {
            std::vector<std::string> etiquetas = { "favorito", "trabajo" };
            Marcador marcador("www.hola.com", "Ejemplo", etiquetas);

            Assert::AreEqual(std::string("www.hola.com"), marcador.getUrl());
            Assert::AreEqual(std::string("Ejemplo"), marcador.getTitulo());
            Assert::AreEqual((size_t)2, marcador.getEtiquetas().size());
            Assert::AreEqual(std::string("favorito"), marcador.getEtiquetas()[0]);
            Assert::AreEqual(std::string("trabajo"), marcador.getEtiquetas()[1]);
        }
        TEST_METHOD(TestGuardarRecuperarMarcador)
        {
            std::vector<std::string> etiquetas = { "lectura", "educación" };
            Marcador marcadorOriginal("www.hola.com", "Ejemplo", etiquetas);

            std::ofstream out("temp.dat", std::ios::binary);
            marcadorOriginal.guardar(out);
            out.close();

            Marcador marcadorRecuperado;
            std::ifstream in("temp.dat", std::ios::binary);
            marcadorRecuperado.recuperar(in);
            in.close();

            Assert::AreEqual(marcadorOriginal.getUrl(), marcadorRecuperado.getUrl());
            Assert::AreEqual(marcadorOriginal.getTitulo(), marcadorRecuperado.getTitulo());
            Assert::AreEqual((size_t)2, marcadorRecuperado.getEtiquetas().size());
            Assert::AreEqual(std::string("lectura"), marcadorRecuperado.getEtiquetas()[0]);
            Assert::AreEqual(std::string("educación"), marcadorRecuperado.getEtiquetas()[1]);

            remove("temp.dat");
        }
        TEST_METHOD(TestCambiarModoIncognito)
        {
            Navegador navegador;
            navegador.cambiarModoIncognitoTabActual();
            Assert::IsTrue(navegador.getModoIncognitoTabActual());

            navegador.cambiarModoIncognitoTabActual();
            Assert::IsFalse(navegador.getModoIncognitoTabActual());
        }
        TEST_METHOD(TestAgregarBuscarMarcador)
        {
            Navegador navegador;
            std::vector<std::string> etiquetas = { "favorito", "trabajo" };
            SitioWeb sitio("www.hola.com", "hola.com", "Ejemplo");
            navegador.agregarMarcador(&sitio);

            navegador.agregarEtiquetas(&sitio);
            std::stringstream ss;
            ss << "Ejemplo";
            navegador.buscarMarcadores(ss.str());

        }

    };
}