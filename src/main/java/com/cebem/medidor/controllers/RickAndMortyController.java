package com.cebem.medidor.controllers;

import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.client.RestTemplate;

@Controller
public class RickAndMortyController {

    private final RestTemplate restTemplate;

    public RickAndMortyController(RestTemplate restTemplate) {
        this.restTemplate = restTemplate;
    }

    @GetMapping("/rickandmorty/random")
    public String getRandomCharacter(Model model) {
        // Hacer una solicitud a la API externa para obtener un personaje aleatorio
        String apiUrl = "https://rickandmortyapi.com/api/character/";
        Character character = restTemplate.getForObject(apiUrl + "1", Character.class); // Aquí puedes usar otro endpoint para obtener un random

        // Agregar el personaje al modelo de Thymeleaf
        model.addAttribute("character", character);

        // Devolver el nombre del template
        return "characterCard";
    }
}
