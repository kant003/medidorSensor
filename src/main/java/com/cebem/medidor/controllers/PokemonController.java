package com.cebem.medidor.controllers;


import lombok.RequiredArgsConstructor;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;

import com.cebem.medidor.models.Pokemon;
import com.cebem.medidor.services.PokemonService;

@Controller
@RequiredArgsConstructor
public class PokemonController {

    private final PokemonService pokemonService;

    @GetMapping("/pokemon")
    public String getPokemonCard(Model model) {
        Pokemon pokemon = pokemonService.getRandomPokemon();
        model.addAttribute("pokemon", pokemon);
        return "pokemon-card";
    }
    
    @GetMapping("/refresh")
    public String refreshPokemonCard() {
        return "redirect:/";
    }
}