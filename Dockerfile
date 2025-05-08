# Etapa de construcción
FROM ubuntu:latest AS build

# Instala Java y dependencias
RUN apt-get update && \
    apt-get install -y openjdk-21-jdk

# Establece directorio de trabajo
WORKDIR /app

# Copia el proyecto completo
COPY . .

# Genera el JAR usando Gradle Wrapper
RUN ./gradlew bootJar --no-daemon

# Etapa de ejecución
FROM openjdk:21-jdk-slim

# Directorio de trabajo para el contenedor final
WORKDIR /app

# Expone el puerto 8080 (usado por Spring Boot)
EXPOSE 8080

# Copia el JAR desde la etapa de build
COPY --from=build /app/build/libs/*.jar app.jar

# Establece el comando de inicio
ENTRYPOINT ["java", "-jar", "app.jar"]
