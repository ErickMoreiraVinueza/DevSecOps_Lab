import joblib
import sys
import os
import argparse

UMBRAL_RIESGO = 0.70 

def cargar_modelo():
    try:
        modelo = joblib.load('modelo_cpp_vuln.pkl')
        vectorizador = joblib.load('vectorizador_cpp.pkl')
        encoder = joblib.load('encoder_etiquetas.pkl')
        return modelo, vectorizador, encoder
    except Exception as e:
        print(f"Error crítico cargando modelos IA: {e}")
        sys.exit(1)

def analizar_archivo(ruta):
    modelo, vectorizador, encoder = cargar_modelo()
    
    print(f"\nAnalizando archivo: {ruta}")
    
    try:
        with open(ruta, 'r', encoding='utf-8', errors='ignore') as f:
            codigo = f.read()
        
        # Extraer caracteristicas, se convierte texto a vectores numéricos (TF-IDF)
        features = vectorizador.transform([codigo])
        
        # Analizar Patrones de Riesgo 
        prediccion_idx = modelo.predict(features)[0]
        amenaza = encoder.inverse_transform([prediccion_idx])[0]
        
        # Obtener la probabilidad más alta
        probs = modelo.predict_proba(features)[0]
        probabilidad_real = probs.max()
        
        print(f"--> Diagnóstico IA: {amenaza}")
        print(f"--> Probabilidad: {probabilidad_real*100:.2f}%")

        # 3. Generar Alertas Automáticas 
        if probabilidad_real > UMBRAL_RIESGO:
            print("\n" + "!"*50)
            print(f"ALERTA DE SEGURIDAD CRÍTICA (Prob > {UMBRAL_RIESGO*100}%)")
            print(f"El archivo '{ruta}' contiene patrones de: {amenaza}")
            print("ACCIÓN: Bloqueando integración en el repositorio.")
            print("!"*50)
            # Retornar código de error 1 hace que GitHub Actions falle
            sys.exit(1) 
        else:
            print("El archivo cumple con los estándares de seguridad.")
            sys.exit(0)

    except Exception as e:
        print(f"Error procesando archivo: {e}")
        sys.exit(1)

if __name__ == "__main__":
    if len(sys.argv) > 1:
        analizar_archivo(sys.argv[1])
    else:
        print("Uso: python scanner.py <archivo.c>")