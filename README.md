# 🦠 Spatiotemporal Modeling of Rabies Using Graph Neural Networks: A Proposal to Enhance Epidemiological Surveillance in Low-Supervision Contexts

This repository contains the full codebase used in the study:  
**"Spatiotemporal Modeling of Rabies Using Graph Neural Networks: A Proposal to Enhance Epidemiological Surveillance in Low-Supervision Contexts"**  
conducted as part of a joint research effort on computational epidemiology in urban Peru.

## 📌 Project Summary

Rabies continues to threaten public health in under-resourced urban settings where under-reporting, poor surveillance, and limited infrastructure complicate timely intervention. This project introduces a Graph Neural Network (GNN)-based framework that models the spread of rabies using a heterogeneous knowledge graph. The graph captures geographic, demographic, epidemiological, and environmental relationships across space and time.

Experiments were conducted using real data from Arequipa, Peru (2016–2024), incorporating city blocks, rabies cases, health posts, and water channels. The core task is a binary classification over urban blocks, predicting future outbreak presence based on historical data.

## 🗂 Repository Structure
- rabies_knowledge_graphs_fase2.ipynb: File used to create knowledge graphs
- paper_IA_2025_fase2.ipynb: File used to run models, optuna, and comparisons.

## 🔍 Features

- **Heterogeneous Knowledge Graph Construction**: integrates spatial units (blocks), rabies cases, health infrastructure, and environmental mobility proxies.
- **Binary Classification Task**: predicts whether a block will be affected by rabies.
- **Edge Attributes and Domain-informed Links**: proximity, health service allocation, environmental factors.
- **Model Architecture**: Message-passing GNN using `SAGEConv` over heterogeneous relations.
- **Baselines**: Includes XGBoost, Random Forest, MLP, and SVM for comparison.
- **Training Setup**:
  - Weighted loss to address class imbalance.
  - 80/20 temporal split for training and validation (2016–2021), with independent test set (2022–2024).
  - Hyperparameter tuning with Optuna.
- **Visualization**: Graph exported to Neo4j for interactive inspection.

## 📊 Results (Test Set 2022–2024)

| Model                  | F1-score | Precision | Recall | Accuracy |
|------------------------|----------|-----------|--------|----------|
| BinaryHeteroGNN        | 0.9655   | 1.0000    | 0.9333 | 0.9988   |
| XGBoost                | 0.6364   | 1.0000    | 0.4667 | 0.9907   |
| Random Forest          | 0.5217   | 0.7500    | 0.4000 | 0.9872   |
| MLP                    | 0.2476   | 0.1444    | 0.8667 | 0.9081   |
| SVM                    | 0.2453   | 0.1429    | 0.8667 | 0.9070   |




