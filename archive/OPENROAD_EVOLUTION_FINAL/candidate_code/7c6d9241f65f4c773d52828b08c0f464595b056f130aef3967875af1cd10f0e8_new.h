// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.46142192;
  double density_weight = 0.56733267;
  double prefix_weight = 0.11459289;
  double neighborhood_weight = 0.19529989;
  double late_weight = 0.01830934;
  double critical_weight = 0.21644520;
  unsigned budget = 7;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
