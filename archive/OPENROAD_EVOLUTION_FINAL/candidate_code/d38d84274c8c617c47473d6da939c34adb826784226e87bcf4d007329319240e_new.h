// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.62909783;
  double density_weight = 0.25540300;
  double prefix_weight = 0.29174537;
  double neighborhood_weight = 0.21321660;
  double late_weight = 0.24408108;
  double critical_weight = 0.12525528;
  unsigned budget = 30;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
