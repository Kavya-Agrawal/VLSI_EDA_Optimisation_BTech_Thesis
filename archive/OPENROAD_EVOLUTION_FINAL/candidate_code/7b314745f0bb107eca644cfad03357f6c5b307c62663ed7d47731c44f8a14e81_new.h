// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.15205031;
  double density_weight = 0.37422810;
  double prefix_weight = 0.46531834;
  double neighborhood_weight = 0.04401757;
  double late_weight = 0.02530569;
  double critical_weight = 0.37279478;
  unsigned budget = 40;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
