// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.54255546;
  double density_weight = 0.59426443;
  double prefix_weight = 0.15892158;
  double neighborhood_weight = 0.20472790;
  double late_weight = 0.08689948;
  double critical_weight = 0.17998230;
  unsigned budget = 11;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
